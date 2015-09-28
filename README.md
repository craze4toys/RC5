# Welcome to use RC5 Encryption Template Class  

------

According to Wiki[^wiki_rc5], RC5 is a symmetric-key block cipher notable for its simplicity. Designed by Ronald Rivest in 1994. RC stands for "Rivest Cipher", or alternatively, "Ron's Code" (compare RC2 and RC4). The Advanced Encryption Standard (AES) candidate RC6 was based on RC5.

As far as I know, openssl, crypto++ and other crytion libraries offer support of RC5 encryption. However, most of them only support 64/128-bit block length. Sometimes, we only need some simple encryption on 32-bit data, and the data is not so sensitive or we don't realy care about cracking the code. In this scenario, 32-bit block length RC5 is useful.

This RC5 template class is an implementation of Rivest's paper[^r_paper], and it supports fully 32/64/128-bit block length.

[^wiki_rc5]: https://en.wikipedia.org/wiki/RC5
[^r_paper]: http://people.csail.mit.edu/rivest/Rivest-rc5rev.pdf
