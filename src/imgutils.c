#include "cub.h"

t_img *loadimg(t_cub *cub, char *file)
{
    t_img *img;

    img = malloc(sizeof(t_img));
    if (!img)
        return (NULL);
    img->img = mlx_xpm_file_to_image(cub->mlx_ptr, file, &img->width, &img->height);
    if (!img->img)
    {
        free(img);
        return (NULL);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    return (img);
}

t_img *newimg(t_cub *cub, int width, int height)
{
    t_img *img;

    img = malloc(sizeof(t_img));
    if (!img)
        return (NULL);
    img->img = mlx_new_image(cub->mlx_ptr, width, height);
    img->width = width;
    img->height = height;
    if (!img->img)
    {
        free(img);
        return (NULL);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    return (img);
}

void destroyimg(t_cub *cub, t_img *img)
{
    if (!img)
        return;
    mlx_destroy_image(cub->mlx_ptr, img->img);
    free(img);
}

int getpixel(t_img *img, int x, int y)
{
    char *pixel;
    int color;

    x = CLAMP(x, 0, img->width);
    y = CLAMP(y, 0, img->height);
    pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

void drawpixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < img->width && y >= 0 && y < img->height)
    {
        dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}
