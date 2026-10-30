double sin(double x) {
#if defined(__i386__) || defined(__x86_64__)
    float xf = (float)x;
    asm volatile("flds (%0)\n\t" // load into ST(0)
                 "fsin\n\t"
                 "fstps (%1)\n\t" // pop off ST(0)
                 : "=r"(xf)
                 : "r"(xf));
    return (double)xf;
#else
#warning "sine not implemented for this architecture"
    return 4.0;
#endif
}

double cos(double x) {
#if defined(__i386__) || defined(__x86_64__)
    float xf = (float)x;
    float *xfp = &xf;
    asm volatile("flds (%0)\n\t" // load into ST(0)
                 "fcos\n\t"
                 "fstps (%1)\n\t" // pop off ST(0)
                 : "=r"(xfp)
                 : "r"(xfp));
    return (double)xf;
#else
#warning "cosine not implemented for this architecture"
    return 4.0;
#endif
}

double fabs(double x) {
    return x < 0 ? -x : x;
}

int abs(int n) {
    return n < 0 ? -n : n;
}
