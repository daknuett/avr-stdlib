/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.
 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.
 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

/* random.c: provide hardware based random functions */

unsigned int seed;

/* block cipher aehnlicher random algorithmus */
unsigned char randr_last;

#define RANDR_PIN	27

void random_begin(unsigned int __seed)
{
	seed=__seed;
	randr_last = analog_read(RANDR_PIN);
}

char random_char(void)
{
	unsigned char phys_randr = analog_read(RANDR_PIN);
	// let the random be a nicer number
	unsigned char mod_randr;
	mod_randr = (seed >> 8) ^ randr_last;
	mod_randr ^= (seed ) ^ phys_randr;
	mod_randr = mod_randr % phys_randr;
	randr_last = phys_randr;
	return mod_randr;
}

unsigned int random_int(void)
{
	unsigned char randr_h,randr_l;
	randr_h = random_char();
	randr_l = random_char();
	
	// swap bytes
	unsigned int inverted_seed;
	inverted_seed = (seed << 8);
	inverted_seed |= (seed >> 8);
	
	inverted_seed ^= randr_l;
	inverted_seed ^= randr_h << 8;

	return inverted_seed;
}

void random_update(void)
{
	randr_last = analog_read(RANDR_PIN);
}
