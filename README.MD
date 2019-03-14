# Othhelo
This is not othello, is this?  
終了判定が若干おかしいかも
# ビルド
Windowsの時はSDLの公式サイトからDevelopment Librariesをダウンロードして  
プロジェクトのルートフォルダにおいてください  
現在のコミットではSDL2-2.0.8とSDL2_net-2.0.1が必要ですが  
VSのソリューションのライブラリパス/インクルードパスを書き換えることによって  
別のバージョンでも使用できます  
VisualStudio2017でプロジェクトをビルドしてください  
  
Linuxでは"Boxer"を使用しているため、cloneするときは  
`git clone --recursive https://github.com/pepepper/Othhelo.git`  
または  
`git clone https://github.com/pepepper/Othhelo.git & git submodule init & git submodule update`  
としてください  
その後CMakeしてください  

# 実行
SDL2 SDL2_netが必要です ただしWindows版のリリースにはDLLファイルを同梱します  
実行するとプロンプトが表示されて質問されるので半角数字で入力してください  
  
では良いガバオセロライフを！
