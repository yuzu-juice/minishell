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

# pre-commit

commit 時に以下のコマンドが自動実行されます。

通らないと、commit できない仕様になっています。

- `norminette`

# GitHub Actions

## CI

全てのブランチへの push 時および、main ブランチへの merge 時に CI が走ります。

CI では、以下のコマンドが自動実行され、テストを実施されます。

- `norminette`
- `make`

  すばらしい

