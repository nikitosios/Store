call plug#begin('~/.vim/plugged/')
Plug 'scrooloose/nerdtree', { 'on': 'NERDTreeToggle' }
Plug 'jiangmiao/auto-pairs'
Plug 'tpope/vim-fugitive'
Plug 'airblade/vim-gitgutter'
Plug 'ctrlpvim/ctrlp.vim'
Plug 'morhetz/gruvbox'
call plug#end()
syntax on
colorscheme gruvbox
set background=dark
set number
set softtabstop=4
set tabstop=4
set shiftwidth=4
set noexpandtab
set exrc
set secure
set hlsearch
set incsearch
augroup project
	autocmd!
	autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END
let &path.="src/include,/usr/include/AL,src,"
map <F5> :!make<CR>
map <F7> :!~/.vim/scr.sh<CR>
map <F6> ==j100h
map <F4> 1000<F6>
map <F9> :!make<CR>:!~/.vim/scr.sh<CR>
map <C-n> :NERDTreeToggle<CR>
