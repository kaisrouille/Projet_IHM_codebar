#include <mbed.h>
#include <threadLvgl.h>

#include "demos/lv_demos.h"
#include <cstdio>

ThreadLvgl threadLvgl(30);
BufferedSerial codebar(D1, D0, 9600); // initialise la communication UART
// partie initilisation de mes objets Lvgl
lv_obj_t *btn = lv_btn_create(lv_scr_act());
lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
lv_obj_t *btn3 = lv_btn_create(lv_scr_act());
lv_obj_t *obj2;
lv_obj_t *img1 = lv_img_create(lv_scr_act());
lv_obj_t *label = lv_label_create(btn);
lv_obj_t *labe2;
lv_obj_t *labe3;
lv_obj_t * obj1 = lv_obj_create(lv_scr_act());
lv_obj_t * obj3 = lv_obj_create(lv_scr_act());
lv_obj_t *labe4= lv_label_create(btn2);// Déplacer la déclaration ici
lv_obj_t *labe5=lv_label_create(obj1);
lv_obj_t *labe6=lv_label_create(btn3);
lv_obj_t *labe7;

// déclaration des outils neccesaire a la lecture de code barre
const char *ficheproduit[50] = {"Banane", "coca", "pattes", "pesto", "vin blanc", "imprimante","champagne","brownie"}; // nom des produits
string chaine;
string produit[50] = {"14810", "1805281", "936283", "921454", "323468", "188647", "071757", "545505","572410","540620"};// code barre utilisé pour cette ihm
int prix [50]={2,4,6,8,14,315,90,5}; // prix de chaque article
int total; // prix total
string cb_caisse = "1212";
std::string donnees_scannees;
char addition[30];
char addition2[30];
int paiement;

static void btn_event_cb(lv_event_t *e) // evenement déclenché par le 1er bouton
{
    LV_LOG_USER("clicked");

    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN); // rend invisible le bouton pressé
 // rend visible tout les objets
    lv_obj_clear_flag(obj2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(img1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(btn2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(btn3, LV_OBJ_FLAG_HIDDEN);


}
static void btn_event_cb2(lv_event_t *e) // evenement déclenché par le 2eme bouton
{
    LV_LOG_USER("clicked");

    lv_obj_t *btn2 = lv_event_get_target(e); // cible l'objet Btn2
    //rend les objet invisible
    lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn3, LV_OBJ_FLAG_HIDDEN);
// rend obj1 visible
    lv_obj_clear_flag(obj1, LV_OBJ_FLAG_HIDDEN);
// crée un objet et initialise ses paramètres
    lv_obj_set_size(obj1, 400, 250);
    lv_obj_set_style_bg_color(obj1, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_label_set_text(labe5,addition2);
    lv_obj_center(obj1);
    lv_obj_center(labe5);
 // variable crée pour savoir si on se situe dans le Btn_event_cb2
    paiement=0;
}
static void btn_event_cb3(lv_event_t *e)
{
    LV_LOG_USER("clicked");

    lv_obj_t *btn3 = lv_event_get_target(e);
    //rend les objet invisible
    lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn3, LV_OBJ_FLAG_HIDDEN);
// rend un objet visible
    lv_obj_clear_flag(obj3, LV_OBJ_FLAG_HIDDEN);
// crée un objet et initialise ses paramètres
    lv_obj_set_size(obj3, 400, 250);
    lv_obj_set_style_bg_color(obj3, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_label_set_text(labe7,"appeler la caissière");
    lv_obj_center(obj3);
    lv_obj_center(labe7);
  // variable crée pour savoir si on se situe dans le Btn_event_cb3
    paiement=1;

    
   
}
// fonction servant a parametrer mes objets
void bouton(void)
{
    lv_obj_set_size(btn, 400, 250);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_label_set_text(label, "Touche pour commencer");
    lv_obj_center(label);
    lv_obj_center(btn);
}

void bouton2(void)
{
    lv_obj_set_size(btn2, 100, 60);
    lv_obj_add_event_cb(btn2, btn_event_cb2, LV_EVENT_CLICKED, NULL);
    lv_label_set_text(labe4, "paiement");
    lv_obj_center(labe4);
    lv_obj_align(btn2, LV_ALIGN_BOTTOM_MID, -30, 0);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_HIDDEN);
    
}
void bouton3(void)
{
    lv_obj_set_size(btn3, 100, 60);
    lv_obj_add_event_cb(btn3, btn_event_cb3, LV_EVENT_CLICKED, NULL);
    lv_label_set_text(labe6, "Reset");
    lv_obj_center(labe6);
    lv_obj_align(btn3, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    lv_obj_add_flag(btn3, LV_OBJ_FLAG_HIDDEN);
    
}
void logo(void)
{
    LV_IMG_DECLARE(logojcarrefour);
    lv_img_set_src(img1, &logojcarrefour);
    lv_obj_align(img1, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);
    lv_obj_set_size(img1, 124, 90);
    lv_obj_add_flag(img1, LV_OBJ_FLAG_HIDDEN);
}


void Zonedtxt(void)
{
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_shadow_width(&style_shadow, 10);
    lv_style_set_shadow_spread(&style_shadow, 5);
    lv_style_set_shadow_color(&style_shadow, lv_palette_main(LV_PALETTE_BLUE));

    obj2 = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj2, &style_shadow, 0);
    lv_obj_set_size(obj2, 180, 250);
    lv_obj_align(obj2, LV_ALIGN_RIGHT_MID, -10, 0);
    lv_obj_add_flag(obj2, LV_OBJ_FLAG_HIDDEN);

    labe2 = lv_label_create(obj2);
    labe3 = lv_label_create(obj2);
    lv_obj_align(labe3,LV_ALIGN_BOTTOM_LEFT,0,0);


}

int main()
{
    int i;
    total=0;
    threadLvgl.lock();
    lv_obj_add_flag(obj1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj3, LV_OBJ_FLAG_HIDDEN);
    bouton();
    Zonedtxt();
    logo();
    bouton2();
    bouton3();
    threadLvgl.unlock();

    while (1)
    {
        if (codebar.readable()) // conditions permettant de savoir si on a recu quelque chose de lisible sur la liaison uart
        {
            threadLvgl.lock();
            char data;
            codebar.read(&data, 1);// fonction permettant de lire les valeurs envoyé sur la liaison UART
            printf("%c", data);// ecris les valeurs recu a la suite
            if (data == '\r')// detecte le dernier caractère du code barre 
            {   
                printf("\n");// ecris un saut de ligne pour que la chaine puisse être ecrite dans le terminale
                printf("%s",chaine);
                for (i = 0; i < 50; i++)
                {
                    if (chaine == produit[i])
                    { printf("cc");
                        lv_label_set_text(labe2, ficheproduit[i]); // Mettre à jour le texte du label
                        total=total+prix[i];// addition de toute les sommes lu pour crée le total
                        snprintf(addition,sizeof(addition),"total: %d e",total); // permet d'ecrire dans une variable pour l'afficher sur lvgl
                        snprintf(addition2,sizeof(addition2),"paie vite  %d e",total);

                        lv_label_set_text(labe3,addition); // Mettre à jour le texte du label
                        
                    }
                    else if (chaine == produit[8] && paiement==0) // condition pour rentre dans le bouton de paiement accepter
                    {
                        lv_label_set_text(labe5,"paiement accepter ");
                            lv_obj_set_style_bg_color(obj1, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);

                    }
                    else if(chaine != produit[8] && paiement==0)// condition pour rentrer dans le cas paiement refusé
                    {lv_label_set_text(labe5,"paiement refuser ");
                    
                    lv_obj_set_style_bg_color(obj1, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
                       


                    }
                    else if (chaine == produit[9] && paiement==1) // condition de réinitialisation 
                    {
                       
                    }

                    
                }

                chaine = "";
            }
            else
            {
                chaine = chaine + data;// permet de stocker les codes barres dans une variable
            }
            threadLvgl.unlock();
        }
        ThisThread::sleep_for(10ms);
    }
}
