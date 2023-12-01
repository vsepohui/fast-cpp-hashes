#include <stdio.h>
#include <string.h>
#include <map>



class Hash {
	public: 
		Hash() {
		};
		
		int value;

		std::map <char,Hash*> node;
		

		int get (char* key) {
			Hash* index = this;
			int len = strlen(key);
				
			for (int i = 0; i < len; i++) {
				if (index->node[key[i]] == NULL) {
					return NULL;
				}
				index = index->node[key[i]];
			}
			return index->value;
		}
		
		int set (char* key, int val) {
			Hash* index = this;
			int len = strlen(key);
			for (int i = 0; i < len; i++) {
				if (index->node[key[i]] == NULL)
					index->node[key[i]] = new Hash;
				index = index->node[key[i]];
			}
			index->value = val;
			return val;
		}
};

int main () {
	Hash *h = new Hash;
	
	printf ("%i\n", h->set("asd", 123));
	printf ("%i\n", h->get("asd"));
	printf ("%i\n", h->set("asd2", 1234));
	printf ("%i\n", h->set("asd3", 12356));
	
	printf ("%i\n", h->get("asd"));
	
	
}
