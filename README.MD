# Othhelo
This is not othello, is this?  
終了判定が若干おかしいかも
# ビルド
Windowsの時はSDLの公式サイトからDevelopment Librariesをダウンロードして  
プロジェクトのルートフォルダに置く  
現在のコミットではSDL2-2.0.8が必要  
VSのソリューションのライブラリパス/インクルードパスを書き換えることによって別のバージョンでも使用可  
またOpenSSLの開発用のファイルなども https://slproweb.com/products/Win32OpenSSL.html などからダウンロード  
VisualStudio2017用プロジェクトファイルを同梱  
  
Linuxでは"Boxer"を使用しているため、cloneするときは  
`git clone --recursive https://github.com/pepepper/Othhelo.git`  
または  
`git clone https://github.com/pepepper/Othhelo.git && git submodule init && git submodule update`  
として  
その後CMake  

# 実行
SDL2とOpenSSLが必要 ただしWindows版のリリースにSDLのDLLファイルは同梱  
OpenSSLのWindows版コンパイル済みバイナリは https://slproweb.com/products/Win32OpenSSL.html などからダウンロード  
実行するとプロンプトが表示されて質問されるので半角数字で入力  
  
では良いガバオセロライフを！
