# ローカルでの初期設定

`git clone` した直後に、以下のコマンドを実行して初期設定を行います。
## 校舎PCでのセットアップ
1. uv のインストール

   ```
   $ pip install uv
   ```

2. python の仮想環境構築

   ```
   $ python3 -m uv sync
   $ source .venv/bin/activate
   ```

3. ライブラリのインストール確認

   ```
   $ norminette -v
   ```

## 自分のPCでのセットアップ
1. uv のインストール

   ```
   $ pip install uv
   ```

2. python の仮想環境構築

   ```
   $ python3 -m uv sync
   $ source .venv/bin/activate
   ```

3. ライブラリのインストール確認

   ```
   $ norminette -v
   ```

## 自分のPCでのセットアップ
1. Dev Containerの立ち上げ
VSCodeを起動したら、右下に Rebuild and Reopen in Container みたいなのが出てくるので、それをクリック

2. python の仮想環境構築

   ```
   $ source .venv/bin/activate
   ```

3. ライブラリのインストール確認

   ```
   $ norminette -v
   ```

ここまで実行が完了すれば、開発を始めることができます！

# pre-commit

commit 時に以下のコマンドが自動実行されます。

通らないと、commit できないように設定しています。

- `norminette`

# GitHub Actions

## CI

全てのブランチへの push 時および、main ブランチへの merge 時に CI が走ります。

CI では、以下のコマンドが自動実行されることでテストが実施されます。

```
$ norminette
$ make
$ valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

# GitHub Projects

GitHub Projects については、[こちら](https://github.com/yuzu-juice/minishell/wiki/GitHub-Projects-運用ガイド)を参照してください。
