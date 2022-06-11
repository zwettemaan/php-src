--TEST--
test1() Basic test
--EXTENSIONS--
tightener
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension tightener is loaded and working!
NULL
