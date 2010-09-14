#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <gtk/gtk.h>
#include <pango/pango-layout.h>
#include <X11/Xlib.h>
#include <pango/pango-layout.h>

GtkWidget * redraw;
GdkPixbuf * srcpix;
GdkPixbuf * despix;
GdkPixbuf * des2pix;
GdkPixbuf * basepix;

int done=0;

int rn(int n){
    int res=0;
    int i;

    i=rand();
    if (i<0){
        i=i*-1;
    }
    i=i%n;
    i++;

    res=i;

    return res;
}

static int
red_pixel (GdkPixbuf *pixbuf, int x, int y)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;
    int red=0;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
//  p[0] = red;
//  p[1] = green;
//  p[2] = blue;
//  p[3] = alpha;
    red=p[0];

    return red;
}

static int
green_pixel (GdkPixbuf *pixbuf, int x, int y)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;
    int green=0;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
//  p[0] = red;
//  p[1] = green;
//  p[2] = blue;
//  p[3] = alpha;
    green=p[1];

    return green;
}

static int
blue_pixel (GdkPixbuf *pixbuf, int x, int y)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;
    int blue=0;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
//  p[0] = red;
//  p[1] = green;
//  p[2] = blue;
//  p[3] = alpha;
    blue=p[2];

    return blue;
}

static int
alpha_pixel (GdkPixbuf *pixbuf, int x, int y)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;
    int alpha=0;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
//  p[0] = red;
//  p[1] = green;
//  p[2] = blue;
//  p[3] = alpha;
    alpha=p[3];

    return alpha;
}

static void
put_pixel (GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
  p[0] = red;
  p[1] = green;
  p[2] = blue;
  p[3] = alpha;
}
     
static void
copy_pixel (GdkPixbuf* src,GdkPixbuf *dst, int x1, int y1, int x2,int y2)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p,*pixels2,*p2;

  n_channels = gdk_pixbuf_get_n_channels (src);

  g_assert (gdk_pixbuf_get_colorspace (src) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (src) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (src);
  height = gdk_pixbuf_get_height (dst);

  g_assert (x1 >= 0 && x1 < width);
  g_assert (y1 >= 0 && y1 < height);

  rowstride = gdk_pixbuf_get_rowstride (src);
  pixels = gdk_pixbuf_get_pixels (src);
 pixels2=gdk_pixbuf_get_pixels(dst);
  p = pixels + y1 * rowstride + x1 * n_channels;
 p2=pixels2+y2*rowstride+x2*n_channels;
//  p[0] = red;
//  p[1] = green;
//  p[2] = blue;
//  p[3] = alpha;
    p2[0]=p[0];
    p2[1]=p[1];
    p2[2]=p[2];
}


static void
pp (GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
 
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
  p[0] = red;
  p[1] = green;
  p[2] = blue;
  p[3] = alpha;
}
     
void pickle(GdkPixbuf * pk,int onx,int omy){
    char reno[100];
    GError **err;

    strcpy(reno,"alout/poo.jpeg");
    reno[6]='0'+onx;
    reno[7]='0'+omy;
    err=NULL;
    gdk_pixbuf_save(pk,reno,"jpeg",err,"quality","100",NULL);
}

void new_images(){
    GError **error;
    int lp;


    error=NULL;
    srcpix=gdk_pixbuf_new_from_file("srcpix.jpg",error);
    error=NULL;
    despix=gdk_pixbuf_new_from_file("despix.jpg",error);
    error=NULL;
    des2pix=gdk_pixbuf_new_from_file("des2pix.jpg",error);
    error=NULL;
    basepix=gdk_pixbuf_new_from_file("base.jpg",error);
}


void load_images(){
    new_images();
}

void change(int ox,int oy){
    int x;
    int y;
    int choice=0;
    int red,gre,blu,alph;
    int ax;
    int ay;

    for (x=2;x<=88;x++){
        for (y=2;y<=88;y++){
            ax=ox+x;
            ay=oy+y;
            red=red_pixel(srcpix,ax,ay);
            gre=green_pixel(srcpix,ax,ay);
            blu=blue_pixel(srcpix,ax,ay);
            alph=alpha_pixel(srcpix,ax,ay);
            pp(basepix,x,y,red,gre,blu,alph);
            //pp(despix,x,y,255,120,0,0);
            //    choice=rn(2);
            //    if (choice==1){
            //        copy_pixel(despix,srcpix,x,y,x,y);
            //    }
            //    if (choice==2){
            //        copy_pixel(des2pix,srcpix,x,y,x,y);
            //    }
            //copy_pixel (srcpix,basepix,x,y,x,y);
        }
    }
   
    pickle(basepix,ox,oy);
}

void change_all(){
    int ox;
    int oy;

    for (ox=1;ox<=9;ox++){
        for (oy=1;oy<=9;oy++){
            change(ox,oy);
        }
    }
}
static gboolean keyPressed(GtkWidget * widget, GdkEventKey * kevt){
    char c;
    c=kevt->string[0];

    gtk_widget_queue_draw_area(redraw,0,0,1000,1000);
    return TRUE;
}



gint drawCanvas(GtkWidget * widget, GdkEventExpose * eevt, gpointer data){
if (done==0){
    change_all();
    done=1;
}
    return TRUE;
}

static gboolean mouseMove(GtkWidget * widget, GdkEventMotion * event){


    gtk_widget_queue_draw_area(redraw,0,0,1000,1000);
    return TRUE;
}



static void byep(GtkWidget * widget, gpointer data){
    gtk_main_quit();
}


int main(int argc2,char * argv2[]){
    GtkWidget * window;
    GtkWidget * canvas;
    GtkWidget * box;


    printf("Starting...\n");

    gtk_init(&argc2,&argv2);

    printf("Gtk inited ...\n");


    // load images
    load_images();

    printf("ready to go...\n");
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    redraw=window;
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(byep),NULL);
    g_signal_connect(G_OBJECT(window),"key_press_event",G_CALLBACK(keyPressed),NULL);   

    canvas=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(canvas),119,79);

    gtk_signal_connect(GTK_OBJECT(canvas),"expose_event",GTK_SIGNAL_FUNC(drawCanvas),NULL);
    gtk_signal_connect(GTK_OBJECT(canvas),"motion_notify_event",GTK_SIGNAL_FUNC(mouseMove),NULL);
    gtk_widget_set_events(canvas,GDK_EXPOSURE_MASK | GDK_POINTER_MOTION_MASK);

    box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),canvas,TRUE,FALSE,0);

    gtk_widget_show(canvas);
    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show(box);

    gtk_window_set_default_size(GTK_WINDOW(window),120,80);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
