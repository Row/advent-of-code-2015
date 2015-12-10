<?php
//
//  day4.php
//  advent-of-code
//
function findMD5Prefix($prefix, $stringFormat) {
    $i = 0;
    $check = '';
    $length = strlen($prefix);
    do {
        $md5 = md5($stringFormat . $i++);
    } while(substr($md5, 0, $length) !== $prefix);
    return $i - 1;
}

assert(findMD5Prefix("00000", "abcdef") == 609043);
assert(findMD5Prefix("00000", "pqrstuv") == 1048970);

$input = "iwrupvqb";
printf("Found match %s for check %d\n\n", $input, findMD5Prefix("00000", $input));
printf("Found match %s for check %d\n\n", $input, findMD5Prefix("000000", $input));
