<?php

date_default_timezone_set(‘Asia/Tokyo’);//タイムゾーンの設定

mb_internal_encoding(“UTF-8”);

$mv = $_GET[“temp”];

$fhandle = fopen(“./log.csv”, “a+”);

//現在時刻の取得
fwrite($fhandle,date(“Y/m/d G:i”));
fwrite($fhandle,”,”);
fwrite($fhandle,$temp);
fwrite($fhandle, “\n”);


header(“Content-type: text/html”);
echo “data=”;
echo $mv;
echo “C\n”;