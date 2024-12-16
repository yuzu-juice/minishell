# ローカルでの初期設定

`git clone` した直後に、以下のコマンドを実行して初期設定を行います。

1. uv のインストール

```
$ pip install uv
```

2. python の環境構築

```
$ uv sync
$ source ./venv/bin/activate
```

3. ライブラリのインストール確認

```
$ norminette -v
$ pre-commit -V
```

4. pre-commit の設定

```
$ pre-commit install
```
