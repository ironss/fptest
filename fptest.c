#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define xy_MAX 10000000
uint32_t px[xy_MAX];
uint32_t py[xy_MAX];


typedef struct
{
    int n;
    double sum_x;
    double sum_x2;
    double sum_y;
    double sum_y2;
    double sum_s2;
    double sum_s2x;
    double sum_s2y;
} stats_t;


void stats_clear(stats_t * stats)
{
    stats->n = 0;
    stats->sum_x = 0.0;
    stats->sum_x2 = 0.0;
    stats->sum_y = 0.0;
    stats->sum_y2 = 0.0;
    stats->sum_s2 = 0.0;
    stats->sum_s2x = 0.0;
    stats->sum_s2y = 0.0;
}


stats_t g_stats;
int process_gstats(uint32_t * px, uint32_t * py, int xy_size)
{
    int i;

    double x;
    double x2;
    double y;
    double y2;
    double s2;

    for (i=0; i < xy_MAX; i++)
    {
        x = (double)px[i];
        y = (double)py[i];
        x2 = x*x;
        y2 = y*y;
        s2 = x2 + y2;
        
        g_stats.sum_x += x;
        g_stats.sum_y += y;
        g_stats.sum_x2 += x2;
        g_stats.sum_y2 += y2;
        g_stats.sum_s2 += s2;
        g_stats.sum_s2x += s2*x;
        g_stats.sum_s2y += s2*y;
        
        g_stats.n += 1;
    }
}

int process2(uint32_t * px, uint32_t * py, int xy_size, stats_t * stats)
{
    int i;

    double x;
    double x2;
    double y;
    double y2;
    double s2;

    for (i=0; i < xy_MAX; i++)
    {
        x = (double)px[i];
        y = (double)py[i];
        x2 = x*x;
        y2 = y*y;
        s2 = x2 + y2;
        
        stats->sum_x += x;
        stats->sum_y += y;
        stats->sum_x2 += x2;
        stats->sum_y2 += y2;
        stats->sum_s2 += s2;
        stats->sum_s2x += x2*x;
        stats->sum_s2y += y2*y;
        
        stats->n += 1;
    }
}

int process3(uint32_t * px, uint32_t * py, int xy_size, stats_t * stats)
{
    int i;

    double x;
    double y;

    for (i=0; i < xy_MAX; i++)
    {
        x = (double)px[i];
        y = (double)py[i];
        
        stats->sum_x += x;
        stats->sum_y += y;
        stats->sum_x2 += x*x;
        stats->sum_y2 += y*y;
        stats->sum_s2 += x*x + y*y;
        stats->sum_s2x += (x*x + y*y)*x;
        stats->sum_s2y += (x*x + y*y)*y;
        
        stats->n += 1;
    }
}

int main(int argc, char *argv)
{
    int i;

    printf("sizeof(int): %d\n", sizeof(int));
    
    for (i=0; i < xy_MAX; i++)
    {
        px[i] = i;        
        py[i] = 2*i;
    }

#if 0
    {
        stats_clear(&g_stats);
        clock_t t1 = clock();
        process_gstats(px, py, xy_MAX);    
        clock_t t2 = clock();
        int duration_ticks = t2 - t1;
        double duration_s = (double)duration_ticks / CLOCKS_PER_SEC;
        printf("g_stats: %d %f %d %f %f %f %f %f %f %f\n", duration_ticks, duration_s, g_stats.n, g_stats.sum_x, g_stats.sum_x2, g_stats.sum_y, g_stats.sum_y2, g_stats.sum_s2, g_stats.sum_s2x, g_stats.sum_s2y);
    }
#endif

#if 0
    {
        stats_t s1;
        stats_clear(&s1);
        clock_t t1 = clock();
        process2(px, py, xy_MAX, &s1);    
        clock_t t2 = clock();
        int duration_ticks = t2 - t1;
        double duration_s = (double)duration_ticks / CLOCKS_PER_SEC;
        printf("process2: %d %f %d %f %f %f %f %f %f %f\n", duration_ticks, duration_s, s1.n, s1.sum_x, s1.sum_x2, s1.sum_y, s1.sum_y2, s1.sum_s2, s1.sum_s2x, s1.sum_s2y);
    }
#endif

#if 0    
    {
        stats_t s1;
        stats_clear(&s1);
        clock_t t1 = clock();
        process3(px, py, xy_MAX, &s1);    
        clock_t t2 = clock();
        int duration_ticks = t2 - t1;
        double duration_s = (double)duration_ticks / CLOCKS_PER_SEC;
        printf("process3: %d %f %d %f %f %f %f %f %f %f\n", duration_ticks, duration_s, s1.n, s1.sum_x, s1.sum_x2, s1.sum_y, s1.sum_y2, s1.sum_s2, s1.sum_s2x, s1.sum_s2y);
    }
#endif

    {
        int i;
        int n = 0;
        int threshold = xy_MAX * 80 / 100;
        
        clock_t t1 = clock();
        for (i = 0; i < xy_MAX; i++)
        {
            if (px[i] > threshold)
                n += 1;
        }
        clock_t t2 = clock();
        int duration_ticks = t2 - t1;
        double duration_s = (double)duration_ticks / CLOCKS_PER_SEC;
        printf("threshold: %d %f %d\n", duration_ticks, duration_s, n);
    }

    printf("\n");
    return 0;
}

