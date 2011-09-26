for directory in $(find -mindepth 1 -type d);
do
    i=1
    FILES=$directory/*
    for f in $FILES;
    do
    base=${f%.*}
    ext=${f#$base}
    mv "$f" "$directory/$i$ext"
    i=$((i + 1))
    done
done
