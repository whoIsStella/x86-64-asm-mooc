/* reference.c — clamp function for compiler-output comparison.
 *
 * Compile with -O0 and -O2 and compare the generated assembly to see
 * how the optimizer eliminates branches and stack traffic.
 *
 *   gcc -O0 -S -masm=intel -o build/clamp_O0.s reference.c
 *   gcc -O2 -S -masm=intel -o build/clamp_O2.s reference.c
 */

int clamp(int x, int lo, int hi)
{
    if (x < lo)
        return lo;
    if (x > hi)
        return hi;
    return x;
}
