" auto-install vim-plug
if empty(glob('~/.config/nvim/autoload/plug.vim'))
  silent !curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs
    \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  "autocmd VimEnter * PlugInstall
  "autocmd VimEnter * PlugInstall | source $MYVIMRC
endif

call plug#begin('~/.config/nvim/autoload/plugged')

" Better Syntax Support
Plug 'sheerun/vim-polyglot'
" File Explorer
Plug 'iamcco/markdown-preview.nvim', { 'do': 'cd app & yarn install'  }
Plug 'scrooloose/nerdtree'
" Auto pairs for '(' '[' '{'
Plug 'jiangmiao/auto-pairs'

Plug 'puremourning/vimspector'

Plug 'https://github.com/leafgarland/typescript-vim'
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'dbakker/vim-projectroot'
Plug 'itchyny/lightline.vim'
Plug 'vim-ruby/vim-ruby'
"Plug 'airblade/vim-gitgutter'


Plug 'vimlab/split-term.vim'

Plug 'junegunn/fzf', {'dir': '~/.fzf', 'do': './install -all' }
Plug 'junegunn/fzf.vim'
"Plug 'junegunn/seoul256.vim'
Plug 'tpope/vim-fugitive'
"Plug 'junegunn/gv.vim'
"Plug 'junegunn/vim-emoji'

Plug 'mrjones2014/dash.nvim', { 'do': 'make install' }
Plug 'kristijanhusak/vim-carbon-now-sh'

Plug 'vim-scripts/L9'
Plug 'vim-scripts/ack.vim'

Plug 'vim-scripts/FuzzyFinder'
Plug 'vim-scripts/ScrollColors'
Plug 'vim-scripts/ShowMarks7'
Plug 'vim-scripts/TagBar'
Plug 'vim-scripts/a.vim'

Plug 'vim-scripts/closetag.vim'
"Plug 'fholgado/minibufexpl.vim'
Plug 'vim-scripts/matchit.zip'

Plug 'morhetz/gruvbox'
"Plug 'git://git.wincent.com/command-t.git'
Plug 'rstacruz/sparkup', {'rtp': 'vim/'}

Plug 'tpope/vim-abolish'
Plug 'Lokaltog/vim-easymotion'
Plug 'ronakg/quickr-cscope.vim'
Plug 'neoclide/coc.nvim', {'branch': 'release'}

Plug 'SirVer/ultisnips'
Plug 'honza/vim-snippets'

Plug 'vim-scripts/wordlist.vim'
Plug 'gmarik/ingretu'
Plug 'vim-scripts/gitv'
Plug 'udalov/kotlin-vim'

Plug 'https://github.com/cdelledonne/vim-cmake.git'
"Plug 'jackguo380/vim-lsp-cxx-highlight'

" Haskel
Plug 'nvim-lua/plenary.nvim'

call plug#end()