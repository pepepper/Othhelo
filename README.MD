# Othhelo
This is not othello, is this?  
終了判定はあまりあてにならない(後述)  
OpenSSL(https://www.openssl.org/)とOpenSiv3D(https://github.com/Siv3D/OpenSiv3D)を使用しています
# ビルド
https://siv3d.github.io/ja-jp/ をもとにOpenSiv3Dをインストール  
またOpenSSLの開発用のファイルなども https://slproweb.com/products/Win32OpenSSL.html などからダウンロード  
VisualStudio2019用プロジェクトファイルを同梱  


# 実行
バイナリリリースは64bit版のみ OpenSSLのライブラリを同梱  
OpenSSLが必要  
OpenSSLのWindows版コンパイル済みバイナリは https://slproweb.com/products/Win32OpenSSL.html などからダウンロード  

# 設定
起動時に表示される設定画面でどのようにプレイするか設定できます  
ゲームモード-オフラインかオンラインで遊ぶかの指定です  
  
オンライン/オフライン共通設定
サイズ指定-盤面のサイズ指定です 実際のサイズは指定したサイズの二倍になります 指定しないときは8x8以上でランダムです  
  
オンライン設定
IPアドレス/ドメイン-オンラインモードで使用するサーバーの指定です  
オンラインモード-ホストとして部屋を作成、ゲストとして部屋に参加、オートマッチでサーバーにお任せ  
パスワード-鍵をかけたいときに

# プレイ
オセ□みたいな何かですがところどころ違います  
盤面のサイズは表示されません 手探りで行きましょう  
Fキーを押すと全くオセロではない何かになります(終了判定が怪しくなる原因)  
Eキーでプレイを終了し設定に戻ります  
Escキーまたは右上Xボタンで終了します

