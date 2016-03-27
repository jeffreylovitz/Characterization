Characterization is a C program that calculates the frequency of associations between words in a given corpus.

It functions by selecting a key word (currently the first word after a period, but hopefully later it will be able to select characters instead) and making a struct for every other word in the sentence.  This struct contains the key word, the value word, and the frequency of the pairing (1 on insertion).

The struct is hashed by taking ((sum of key words' int representation's digits * 31) % 100).  Since only the key word is used in the hash function, every pair in the sentence will collide in the same bucket.  Thus, each bucket will contain a series of structs that share a key word (though hash values are not distinct, and thus each bin will also contain multiple key words).  By iterating through these lists, patterns are detected.

