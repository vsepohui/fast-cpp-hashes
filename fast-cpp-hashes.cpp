#include <stdio.h>
#include <string.h>
#include <map>
#include <cstdlib>



class Hash {
	public: 
		Hash() {
		};
		
		int value;
		int cnt = 0;

		std::map <char,Hash*> node;
		

		int get (char* key) {
			Hash* index = this;
			int len = strlen(key);
				
			for (int i = 0; i < len; i++) {
				if (index->node[key[i]] == NULL) {
					return 0;
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
				index->cnt ++;
			}
			index->value = val;
			return val;
		}
		
		int deleting (char* key) { 
			Hash* index = this;
			Hash **ref;
			int result;
			int len = strlen(key);
			ref = (Hash **)malloc(sizeof(Hash*) * len);
			for (int i = 0; i < len; i++) {
				index->node[key[i]]->cnt --;
				index = index->node[key[i]];
				ref [i] = index;
			}
			result = index->value;
			for (int i = len - 1; i >= 0; i--) {
				if (ref[i]->cnt == 0) {
					delete (ref[i]);
				} else {
					break;
				}
			}
			free (ref);
			return result;
		}
		
		int renaming(char* key, char *key2) {
			return this->set(key2, this->deleting(key));
		}
};

int main () {
	Hash *h = new Hash;
	
	printf ("%i\n", h->set("asd", 123));
	printf ("%i\n", h->get("asd"));
	printf ("%i\n", h->set("asd2", 1234));
	printf ("%i\n", h->set("asd3", 12356));
	
	printf ("%i\n", h->get("asd"));
	printf ("%i\n", h->deleting("asd"));
	printf ("%i\n", h->renaming("asd3", "kush"));
	printf ("%i\n", h->get("kush"));
	
	
}
