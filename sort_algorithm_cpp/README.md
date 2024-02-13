# sort_algorithm
## build
```sh
mkdir build
cd build
cmake ..
make
```

## sort
```sh
./sort <sequcence file> <answer file> <algorithm name> <enable print>
```

- <algorithm name> (optional) : `standard` or `quick`
- <enable print> (optional) : `print`を指定すればソート前後の数列を出力

## sorting_timer

## sequence_generator
乱数により数列を生成．答え(ソート済み数列)も同時に出力．

```sh
./sequence_generator <sequcence size> <output sequcence file> <output answer(sorted) file>
```

例:
```sh 
./sequence_generator 100 sequcences/s100.txt answers/a100.txt
```

サイズ100の数列を`sequences/s100.txt`に，ソート済みを`answers/a100.txt`に出力．


## multiple_sequence_generator
数列ファイルをまとめて生成．

```sh
./multiple_sequence_generator <sequcence size> <num files> <output sequences dir> <output answers dir> <sequence file name prefix> <answer file name prefix>
```

- <sequence file name prefix> <answer file name prefix> : optional

例:
```sh
./multiple_sequence_generator 10 5 sequcences answers s a 
```
サイズ10の数列を`sequcences`以下に5個生成．ソート済みを`answers`以下に出力．

ファイル名は`s100_0.txt`-`s100_4.txt`，`a100_0.txt`-`a100_4.txt`のようになる．

