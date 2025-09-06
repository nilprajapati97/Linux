#include <stdint.h> // For uint32_t

/**
 * @brief Converts a 32-bit unsigned integer from big-endian to little-endian.
 * @param big_endian_val The 32-bit unsigned integer in big-endian format.
 * @return The 32-bit unsigned integer in little-endian format.
 */
/*
 uint32_t bigEndianToLittleEndian(uint32_t big_endian_val) {
    uint32_t little_endian_val = 0;

    // Extract and reorder bytes
    little_endian_val |= (big_endian_val & 0x000000FF) << 24; // Byte 0 (LSB of big-endian) becomes Byte 3 (MSB of little-endian)
    little_endian_val |= (big_endian_val & 0x0000FF00) << 8;  // Byte 1 becomes Byte 2
    little_endian_val |= (big_endian_val & 0x00FF0000) >> 8;  // Byte 2 becomes Byte 1
    little_endian_val |= (big_endian_val & 0xFF000000) >> 24; // Byte 3 (MSB of big-endian) becomes Byte 0 (LSB of little-endian)

    return little_endian_val;
}
*/

// Example usage:
#include <stdio.h>

int main() {
    uint32_t big_endian_data = (0x11223344 & 0x000000FF )<< 24; // Example big-endian value
//    uint32_t little_endian_data = bigEndianToLittleEndian(big_endian_data);

//    printf("Big-endian: 0x%X\n", big_endian_data);
//    printf("Little-endian: 0x%X\n", little_endian_data);

    return 0;
}
