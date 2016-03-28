Characterization is a C program that calculates the frequency of associations between words in any given corpus.

It functions by selecting 2 key words that match a stored regex pattern (loosely, the format of 2-word proper nouns) and a 3rd word to act as the value.

Both the concatenated keywords and the value are made into a struct and hashed 
by summing the ASCII value of the keywords, multiplying by 31, and taking the
modulo for 100.

structured by a regex but hopefully later it will be able to select characters instead) and making a struct for every other word in the sentence.  This struct contains the key word, the value word, and the frequency of the pairing (1 on insertion).

Since only the key word is used in the hash function and the hash function is
deterministic, each of the 100 buckets will become populated with the different
values matching each key.

The frequency of an exact match is recorded, and a mergesort is performed on
all values associated with each keyword.

Thus, we can look at the results as a tool to help find patterns and associations
between the work's words.
