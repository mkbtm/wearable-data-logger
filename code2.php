<?php

date_default_timezone_set(‘Asia/Tokyo’);//タイムゾーンの設定

mb_internal_encoding(“UTF-8”);//文字コードの設定

$year = $_GET[“year”];
$month = $_GET[“month”];
$day = $_GET[“day”];

$array = file(“./log.csv”);//ファイルの中身を配列にいれる。

header(“Content-type: text/html”);

$i = 0;
$returnString = “”;
foreach ($array as $line) {
    $lineArray = explode(‘,’, $line);
    $logDate = $lineArray[0];
    $logCO2 = $lineArray[1];
    $logCO2 = str_replace(“\n”, ‘’, $logCO2);

    $temp = explode(“ “, $logDate);//日付と時刻を分解する
    $YMD = $temp[0];

    $temp2 = explode(‘/’, $YMD);//年月日を分解する
    $temp_year = $temp2[0];
    $temp_month = $temp2[1];
    $temp_day = $temp2[2];

    $HM = $temp[1];

    if (($temp_year == $year) && ($temp_month == $month)&& ($temp_day == $day)){
        //日付が一致したので値を返す
        //$returnString = $returnString . $logDate . “,” . $logCO2 . “,” . $logTemp . “,” . $logHum . “\n”;
        $returnString = $returnString . $logDate . “,” . $logCO2 . “\n”;
    }
    $i++;
}

//レスポンス
echo $returnString;