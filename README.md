Yomotsuhirasaka / 黄泉平坂 [![New BSD](http://img.shields.io/badge/license-New%20BSD-blue.svg?style=flat)](https://github.com/WCE-ProgrammingTeam/Yomotsuhirasaka/blob/master/LICENSE)
====

これは、ストリーム風のインタフェースをもつ暗号ライブラリです。
ストリーム暗号だけでなく、ブロック暗号にも、同じインタフェースで対応しています。 

サークル活動の中で制作されました。

This is a library for en/decryption.
You can use stream-encryption, and also block-encryption, with stream-like user interface.

This is being produced in the circle activity.

## Description
このライブラリは、暗号化ストリームと復号ストリームで構成されます。
暗号化/復号ストリームの一つのペアは、ひとつの暗号方式に対応しています。
(仮想関数は使われていません。したがって、多態を用いることは出来ません。)

対応している暗号方式は、Arcfour、MUGI、AES、Twofishです。
ブロック暗号であるAESとTwofishに対しては、暗号利用モードを選択出来ます。

This library consists of encrypting/decrypting stream.
One pair of encrypting/decrypting stream correspond to one encryption method.
(In this library, there is no virtual function. So you cannot use polymorphism.)

The suppoted encryption methods are Arcfour, MUGI, AES, and Twofish.
When you use AES or Twofish, you can select block cipher modes of operation.

## Demo

## VS. 

## Requirement
必要なのはSTLだけです。

This library requires STL only.

## Usage
See example.

## Install
このリポジトリをcloneして、yomotsuhirasaka.hppをincludeするだけ。

Clone this repository and include yomotsuhirasaka.hpp.

```
#include "src/yomotsuhirasaka/yomotsuhirasaka.hpp"
```

## Licence
[New BSD](https://github.com/WCE-ProgrammingTeam/Yomotsuhirasaka/blob/master/LICENSE)

## Author
[Waseda Computer Entertainment](https://sites.google.com/site/wasedace/)
