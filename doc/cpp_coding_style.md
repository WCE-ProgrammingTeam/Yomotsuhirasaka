命名規則
===

基本は「小文字アンダーバー区切り」  


### ローカル変数, パラメータ  
```
int variable_name; 
```

###private/protectedメンバ変数
```
int variable\_name_;
```

###publicメンバ変数
```
int variable_name;
```

###関数名, メンバ関数名
```
void func_name();
```

###クラス名
```
class class_name {};
```

###テンプレートパラメータ
パラメータにクラスを要求する(クラスメンバにアクセスしうる)時はclass,  
単に型を要求する時はtypenameとする.

```
template <class TypeName1, typename TypeName2, ...>
...
```

###メタ関数の戻り値名(値)
```
struct ...
{
    static const int value;
};
```

###メタ関数の戻り値名(型)
```
struct ...
{
    typedef
        ...
    type;
};
```

###列挙型(enum type)
列挙定数(アイテム)は単数、列挙型自体も単数形。
```
enum enum_name
{
	 FIRST_ITEM
	,SECOND_ITEM
	,THIRD_ITEM
	,...
};
```

### (C++ではないが)ファイル・フォルダ名
プロジェクト全体のフォルダはパスカルケース、それ以下は(ファイルも含めて)スネークケース。
同じ種類のものをまとめたファイル・フォルダは複数形で命名。

文法
==
スペース位置と有無, 改行, 中カッコの位置と有無, インデント

###関数定義
1行で書くこともある
```
void func_name(int x, int y, int z)
{
}
```

###引数指定
```
func_name(x, y, z);
```

###クラス定義
```
class class_name
{
    ...
};
```

###if文
```
if (...)
    ...

if (...)
{
    ...
    ...
}

if (...)
{
    ...
    ...
}
else
{
    ...
    ...
}

if (...)
    ...
else
    ...

if (...)
    ...
else
if (...)
    ...
else
    ...

if (...)
{
    ...
    ...
}
else
if (...)
{
    ...
    ...
}
else
{
    ...
    ...
}
```

###for文
```
for (int index = 0; index < 10; index++)  
    ...  

for (int index = 0; index < 10; index++)  
{  
    ...  
    ...  
}  
```

###switch文
goto文的な効果を期待して、意図的にbreakを書かないこともある
```
switch (...)  
{  
    case x:  
        ...  
    break;  

    default:  
        ...  
    break;  
}  
```

###名前空間
全てスネークケース。
同じ種類のものをまとめたファイル・フォルダは複数形で命名。
入れ子になってもインデントしない。
```
namespace ns1	{
namespace ns2	{　 // ここにはインデントなし
	...
} } // namespace ns1::ns2
```

---
protectedメンバ変数は基本的には使わない

ublicメンバ変数は構造体としての用途(全てのメンバ変数を公開)の場合のみ
