どうも。

>>> 開発にあたり、まずはtest以下を確認して下さい。
Boost.Build(bjam)とVisualStudio2013でビルドできるようにしてあります。

>>> test/src以下には各班ごとにendecrypt_text.cppを置いています。
今まではひとつのendecrypt_text.cppを使っていたのですが、
このままでは各班ごとのテストが出来ない
(他班担当部分がコンパイルエラーを出したらテストできない)ので、
各班ごとに分けました。

>>> さらに、使おうと思っていたテストフレームワークFCTXがエラー吐いたので、
より使いやすいテストフレームワークCatchに乗り換えます。

>>> test/src以下ファイルの中身は(Arcfourのもの以外は)空です。
そこで、まずは各班で以下の作業を行ってもらいます。
1. test/src/endecrypt_text.cppから、自分の班の担当箇所とinclude部分などを切り出し、
test/src/(担当の暗号方式名)/endecrypt_text.cppに移す。

2. FCT_***のマクロを書き換える。

いずれもtest/src/Arcfour/endecrypt_text.cppを参考にしてください。
コピペだけで終わります。

>>> あとは、心置きなくsrc以下で開発をしてください。
出来る限り、参考になるようにArcfour部分を書きました。
暗号化/復号はestreambuf/dstreambufで行い、
インタフェースはestream/dstreamという感じです。

>> それと、pullはSourceTreeが「pullあるよ」みたいなことを言った時だけでいいです。

>>> では、頑張ってください。twitterでもLINEでも質問は受け付けています。

中辛。2015/01/04記。
