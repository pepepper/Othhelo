# Othhelo
This is not othello, is this?  
終了判定が若干おかしいかも
# ビルド
Windowsの時はSDLの公式サイトからDevelopment Librariesをダウンロードして  
プロジェクトのルートフォルダにおいてください  
現在のコミットではSDL2-2.0.8が必要ですが  
VSのソリューションのライブラリパス/インクルードパスを書き換えることによって別のバージョンでも使用できます 
またOpenSSLの開発用のファイルなども https://slproweb.com/products/Win32OpenSSL.html などからダウンロードしてください
VisualStudio2017用プロジェクトファイルを同梱しています  
  
Linuxでは"Boxer"を使用しているため、cloneするときは  
`git clone --recursive https://github.com/pepepper/Othhelo.git`  
または  
`git clone https://github.com/pepepper/Othhelo.git && git submodule init && git submodule update`  
としてください  
その後CMakeしてください  

# 実行
SDL2とOpenSSLが必要です ただしWindows版のリリースにSDLのDLLファイルは同梱します  
OpenSSLのWindows版コンパイル済みバイナリは https://slproweb.com/products/Win32OpenSSL.html などからダウンロードしてください  
実行するとプロンプトが表示されて質問されるので半角数字で入力してください  
  
では良いガバオセロライフを！
