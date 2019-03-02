# Othhelo
This is not othello, is this?  

# ビルド
Windowsの時はSDLの公式サイトからDevelopment Librariesをダウンロードして  
プロジェクトのルートフォルダにおいてください  
現在のコミットではSDL2-2.0.8が必要ですが CMakeLists.txtにあるSDL2-2.0.8を書き換えることによって  
別のバージョンのSDL2でも使用できます  
VisualStudio等でcppファイルをプロジェクトに追加しビルドしてください  
  
Linuxでは"Boxer"を使用しているため、cloneするときは  
`git clone --recursive https://github.com/pepepper/Othhelo.git`  
または  
`git clone https://github.com/pepepper/Othhelo.git & git submodule init & git submodule update`  
としてください  
その後CMakeしてください  

# 実行
SDL2が必要です ただしWindows版のリリースにはDLLファイルを同梱します  
実行するとプロンプトが表示されて質問されるので半角数字で入力してください  
  
では良いガバオセロライフを！
