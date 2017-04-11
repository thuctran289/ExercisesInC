/* Simple example using Glib.

This program takes in a filename as an arguement, and counts the 
number of times each word in the file appears. 
Written by Thuc Tran


*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

//Writing a comparison function for use in sorting a list. 
//Each hash is assumed to be a hash table structure
//a and b are assumed to be char arrays. 
int GCompare(gconstpointer a, gconstpointer b, gpointer hash)
{
	int vala = (int) g_hash_table_lookup(hash, a);
	int valb = (int) g_hash_table_lookup(hash, b);
	if(vala == valb)
		return 0;
	else
		return vala>valb?1:-1;
}


int main(int argc, char** argv) {
	
	//No error checking, but this gets the file name.
	gchar *content, *filename = argv[1];
	int length;

	//Create a hashtable with default hashing and equality functions. 
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	//Checks to see if the file works and writing it to content
	if (g_file_get_contents (filename, &content, &length, NULL)) {
		//Munging content to remove special characters and capitalization
		content = g_ascii_strdown(content,-1);
		content = g_strdelimit(content, "\a\b\f\n\r\t\v\\\'\"\?\nnn!%@#$‘^&*(){}[]-_=+;':`~'/’.,<>?", ' ');
		//Tokenize the data based on space into an array of words
		gchar ** data = g_strsplit(content, " ", -1);


		while(*data){
			//If the tables doesn't contain the data, add it to the table
			if(g_hash_table_contains(hash, *data)==FALSE)
			{
				g_hash_table_insert(hash, *data, 1);
			}
			else
			{
			//Otherwise increment by one. 
				int val = (int)g_hash_table_lookup(hash, *data);
				val = val+1;
				g_hash_table_replace(hash, *data, val);
			}
			++data;
		}
		//Remove the empty vector in the hash table. 
		g_hash_table_remove(hash, "");

		//Create a list based on the hash table's keys and sorts by number
		//of appearences
		GList* table = g_hash_table_get_keys(hash);
		table = g_list_reverse(g_list_sort_with_data(table, &GCompare, hash));

		//Print the values and key for each entry
		for(int x = 0; x<g_hash_table_size(hash); x++)
		{
			int val = g_hash_table_lookup(hash, table->data);
			printf("%s: %d\n", (char*) table->data, val);
			table = table->next;	
		}
		
		// Process contents
		g_free (content);
	}
    return 0;
}

