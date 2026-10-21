#!/usr/bin/env bash
# Демо к лекции «Полиморфизм в C++: как это устроено внутри».
#   ./run_all.sh        все демо подряд
#   ./run_all.sh 07     одно демо по номеру (00–16, b1–b4)
# Нужны g++ и clang++ (clang — только для дампов раскладки и vtable).
set -u
cd "$(dirname "$0")"
CXX=${CXX:-g++}
CLANG=${CLANG:-clang++}
STD=-std=c++20
B=build
mkdir -p "$B"
ONLY=${1:-}
UNBUF=""; command -v stdbuf >/dev/null && UNBUF="stdbuf -o0"

want() { [ -z "$ONLY" ] || [ "$ONLY" = "$1" ]; }
hdr()  { printf '\n== %s\n' "$*"; }
err1() { "$@" 2>&1 | grep -m1 -E 'error|undefined reference'; }
# asm <файл> <-O> <regex имён>: ассемблер функций в Intel-синтаксисе без служебных строк
asm()  { $CXX $STD "$2" -masm=intel -S -o - "$1" |
           awk -v re="$3" '/^[A-Za-z_.$][^ ]*:$/ && $0 ~ re {p=1} p {print} p && /cfi_endproc/ {p=0; print ""}' |
           grep -vE '^\s*\.(cfi|p2align|size|type|globl|weak|section|set)|endbr64|^\.L[A-Z]+[0-9]+:$'; }
# syms <объектник> <regex>: манглированное имя → нормальное
syms() { nm --defined-only "$1" | awk '$2 ~ /^[TW]$/ {print $3}' | grep -E "$2" |
           while read -r s; do printf '%-36s → %s\n' "$s" "$(c++filt "$s")"; done; }

want 00 && { hdr "00 хук: вызов через объект и через указатель, -O0"
  asm 00_hook.cpp -O0 '^_Z1[01]via_'; }

want 01 && { hdr "01 перегрузка и манглинг"
  $CXX $STD 01_overload.cpp -o $B/01 && $B/01
  $CXX $STD -c 01_overload.cpp -o $B/01.o && syms $B/01.o '^_Z4area'
  echo "MSVC-схема (clang --target=x86_64-pc-windows-msvc):"
  sed '/#include/d; /^int main/,$d' 01_overload.cpp |
    $CLANG $STD --target=x86_64-pc-windows-msvc -x c++ -S -o - - 2>/dev/null |
    grep -oE '^"?\?area[^ :"]*' | tr -d '"' | sort -u; }

want 02 && { hdr "02 перегрузка только по типу возврата"
  err1 $CXX $STD -fsyntax-only 02_return_type.cpp; }

want 03 && { hdr "03 extern \"C\" и две перегрузки"
  err1 $CXX $STD -fsyntax-only 03_extern_c.cpp; }

want 04 && { hdr "04 объявление разошлось с определением"
  echo "с extern \"C\":";  $CXX $STD 04_linkage_c/*.cpp -o $B/04c && $B/04c
  echo "без extern \"C\":"; err1 $CXX $STD 04_linkage_cpp/*.cpp -o $B/04cpp; }

want 05 && { hdr "05 тип возврата в имя не входит"
  $CXX $STD 05_return_mismatch/*.cpp -o $B/05 && $B/05
  $CXX $STD -c 05_return_mismatch/lib.cpp  -o $B/05lib.o
  $CXX $STD -c 05_return_mismatch/main.cpp -o $B/05main.o
  nm $B/05lib.o $B/05main.o | grep -E ' [TU] _Z4half'; }

want 06 && { hdr "06 шаблон порождает функции"
  $CXX $STD 06_template.cpp -o $B/06 && $B/06
  $CXX $STD -c 06_template.cpp -o $B/06.o && syms $B/06.o 'print_area'; }

want 07 && { hdr "07 CRTP"
  $CXX $STD 07_crtp.cpp -o $B/07 && $B/07; }

want 08 && { hdr "08 virtual и разнородный контейнер"
  $CXX $STD 08_virtual.cpp -o $B/08 && $B/08; }

want 09 && { hdr "09 срезка"
  $CXX $STD 09_slicing.cpp -o $B/09 && $B/09; }

want 10 && { hdr "10 абстрактная база по значению"
  err1 $CXX $STD -fsyntax-only 10_abstract.cpp; }

want 11 && { hdr "11 раскладка Circle и её vtable (clang)"
  $CLANG $STD -Xclang -fdump-record-layouts -c 11_layout.cpp -o /dev/null | awk '/\| struct Circle$/,/nvalign/'
  $CLANG $STD -Xclang -fdump-vtable-layouts -c 11_layout.cpp -o /dev/null | awk '/Vtable for .Circle./,/^$/'; }

want 12 && { hdr "12 хвост: POD и не POD"
  $CXX $STD 12_padding.cpp -o $B/12 && $B/12
  $CLANG $STD -Xclang -fdump-record-layouts -c 12_padding.cpp -o /dev/null 2>/dev/null |
    awk '/\| struct (PlainChild|WithCtorChild)$/,/\| \[sizeof/'; }

want 13 && { hdr "13 виртуальный вызов из конструктора"
  $CXX $STD 13_ctor.cpp -o $B/13 && $B/13; }

want 14 && { hdr "14 невиртуальный деструктор: тихо"
  $CXX $STD -Wall 14_dtor_silent.cpp -o $B/14 2>&1 | grep -m1 -o 'warning:.*'
  $B/14; echo "exit=$?"; }

want 15 && { hdr "15 невиртуальный деструктор: громко"
  $CLANG $STD -Xclang -fdump-record-layouts -c 15_dtor_crash.cpp -o /dev/null 2>/dev/null |
    awk '/\| struct PrintableCircle$/,/nvalign/'
  $CXX $STD 15_dtor_crash.cpp -o $B/15 2>/dev/null
  $UNBUF $B/15; echo "exit=$?"; }

want 16 && { hdr "16 цена: virtual, final, CRTP (-O2)"
  asm 16_cost.cpp -O2 '^_Z[0-9]+via_'; }

want b1 && { hdr "Б1 thunk: вызов (-O1) и delete (-O2) через вторую базу"
  asm backup/b1_thunk.cpp -O1 '^_ZThn16_NK15PrintableCircle5print'
  asm backup/b1_thunk.cpp -O2 '^_ZThn16_N15PrintableCircleD0'; }

want b2 && { hdr "Б2 ромб (clang)"
  $CLANG $STD -Xclang -fdump-record-layouts -c backup/b2_diamond.cpp -o /dev/null 2>/dev/null |
    awk '/\| struct Copier$/,/nvalign/'; }

want b3 && { hdr "Б3 шаблонный метод не может быть virtual"
  err1 $CXX $STD -fsyntax-only backup/b3_template_virtual.cpp; }

want b4 && { hdr "Б4 забыли определить виртуальную функцию"
  err1 $CXX $STD backup/b4_undefined_vtable.cpp -o $B/b4; }

exit 0
