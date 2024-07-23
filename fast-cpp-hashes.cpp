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
		
		
		operator bool() {
			return this->node.size() != 0;
		}
		
		Hash * step (char c) {
			Hash *h = this->node[c];
			if(!h) return NULL;
			return h;
		}
		

		int get (char* key) {
			Hash* index = this;
			int len = strlen(key);
				
			for (int i = 0; i < len; i++) {
				index = index->step(key[i]);
				
				if (!index) return 0;
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
				
				if (key[i]) {
					index = index->step(key[i]);
					if (!index) break;
					
					index->cnt --;
								
					ref [i] = index;
				} else {
					break;
				}
			}
			
			
			if (!index) return 0;
			
			
			result = index->value;
			for (int i = len - 1; i >= 0; i--) {
				if (ref[i]->cnt == 0) {
					if (ref[i]) {
						delete (ref[i]);
					} else {
						break;
					}
				} else {
					break;
				}
			}
			
			
			if (ref) free (ref);
			return result;
		}
		
		int renaming(char* key, char *key2) {
			return this->set(key2, this->deleting(key));
		}
};

int main () {
	Hash *h = new Hash;
	
	
	
	printf ("%d\n", h->set("asd", 123));
	printf ("%d\n", h->get("asd"));
	printf ("%d\n", h->set("asd2", 1234));
	printf ("%d\n", h->set("asd3", 12356));
	
	printf ("%d\n", h->deleting("asd54"));	
	printf ("%d\n", h->get("asd"));	
	
	printf ("%d\n", h->get("asd"));
	printf ("%d\n", h->deleting("asd"));
	printf ("%d\n", h->renaming("asd3", "kush"));
	printf ("%d\n", h->get("kush"));
	
	
}
