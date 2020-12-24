syntax on
set number
let mapleader=" "
colorscheme peachpuff
filetype detect
syntax on

call plug#begin('~/.vim/plugged')
Plug 'scrooloose/nerdtree'
call plug#end()

set clipboard+=unnamedplus
set mouse=a
set tabstop=2
set autoindent
set shiftwidth=2
set softtabstop=2
set smarttab
set expandtab
set smartcase
set matchpairs={:},[:],<:>,':',":"
nnoremap <C-y> "+y
vnoremap <C-y> "+y
nnoremap <C-p> "+gP
vnoremap <C-p> "+gP
set backspace=indent,eol,start
set cindent
:imap jj <Esc>
set showcmd
set autowrite
set autoread
map <F5> :<C-U>!g++ -O2 -DLOCAL -std=c++17 -Wall -Wextra -Dnp -static %:r.cpp -o %:r<CR>
