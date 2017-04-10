/* Simple example using Glib.

From http://www.ibm.com/developerworks/linux/tutorials/l-glib/

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

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
	
	gchar *content, *filename = argv[1];
	int length;

	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	if (g_file_get_contents (filename, &content, &length, NULL)) {
		content = g_ascii_strdown(content,-1);
		content = g_strdelimit(content, "\a\b\f\n\r\t\v\\\'\"\?\nnn!%@#$‘^&*(){}[]-_=+;':`~'/’.,<>?", ' ');
		gchar ** data = g_strsplit(content, " ", -1);


		while(*data){
			if(g_hash_table_contains(hash, *data)==FALSE)
			{
				g_hash_table_insert(hash, *data, 1);
			}
			else
			{
				int val = (int)g_hash_table_lookup(hash, *data);
				val = val+1;
				g_hash_table_replace(hash, *data, val);
			}
			++data;
		}

		g_hash_table_remove(hash, "");
		GList* table = g_hash_table_get_keys(hash);
		table = g_list_reverse(g_list_sort_with_data(table, &GCompare, hash));

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

