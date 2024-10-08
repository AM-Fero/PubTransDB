PGDMP  9                    |            Public_Transport_DB    16.0    16.0 5    �           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            �           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            �           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            �           1262    160088    Public_Transport_DB    DATABASE     �   CREATE DATABASE "Public_Transport_DB" WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Russian_Russia.1251';
 %   DROP DATABASE "Public_Transport_DB";
                postgres    false            �            1259    160089    Buses    TABLE     �   CREATE TABLE public."Buses" (
    id_driver integer,
    id_route integer,
    id_depot integer,
    on_line boolean,
    id_type integer,
    year_create integer,
    registration_number text,
    bus_position integer,
    id_bus integer NOT NULL
);
    DROP TABLE public."Buses";
       public         heap    postgres    false            �            1259    168153    Buses_id_buss_seq    SEQUENCE     �   CREATE SEQUENCE public."Buses_id_buss_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 *   DROP SEQUENCE public."Buses_id_buss_seq";
       public          postgres    false    215            �           0    0    Buses_id_buss_seq    SEQUENCE OWNED BY     J   ALTER SEQUENCE public."Buses_id_buss_seq" OWNED BY public."Buses".id_bus;
          public          postgres    false    222            �            1259    160094    Depots    TABLE     O   CREATE TABLE public."Depots" (
    name text,
    id_depot integer NOT NULL
);
    DROP TABLE public."Depots";
       public         heap    postgres    false            �            1259    168163    Depots_id_depott_seq    SEQUENCE     �   CREATE SEQUENCE public."Depots_id_depott_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 -   DROP SEQUENCE public."Depots_id_depott_seq";
       public          postgres    false    216            �           0    0    Depots_id_depott_seq    SEQUENCE OWNED BY     P   ALTER SEQUENCE public."Depots_id_depott_seq" OWNED BY public."Depots".id_depot;
          public          postgres    false    223            �            1259    160099    Drivers    TABLE     Q   CREATE TABLE public."Drivers" (
    name text,
    id_driver integer NOT NULL
);
    DROP TABLE public."Drivers";
       public         heap    postgres    false            �            1259    168173    Drivers_id_driverr_seq    SEQUENCE     �   CREATE SEQUENCE public."Drivers_id_driverr_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 /   DROP SEQUENCE public."Drivers_id_driverr_seq";
       public          postgres    false    217            �           0    0    Drivers_id_driverr_seq    SEQUENCE OWNED BY     T   ALTER SEQUENCE public."Drivers_id_driverr_seq" OWNED BY public."Drivers".id_driver;
          public          postgres    false    224            �            1259    160104    Routes    TABLE     �   CREATE TABLE public."Routes" (
    name text,
    overall_time time(0) without time zone,
    time_first time(0) without time zone,
    time_last time(0) without time zone,
    "interval" time(0) without time zone,
    id_route integer NOT NULL
);
    DROP TABLE public."Routes";
       public         heap    postgres    false            �            1259    160109    Routes-Stops    TABLE     �   CREATE TABLE public."Routes-Stops" (
    id_route integer,
    id_stop integer,
    "position" integer,
    time_to_next time without time zone,
    id_route_stop integer NOT NULL
);
 "   DROP TABLE public."Routes-Stops";
       public         heap    postgres    false            �            1259    168201    Routes-Stops_id_route_stopp_seq    SEQUENCE     �   CREATE SEQUENCE public."Routes-Stops_id_route_stopp_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 8   DROP SEQUENCE public."Routes-Stops_id_route_stopp_seq";
       public          postgres    false    219            �           0    0    Routes-Stops_id_route_stopp_seq    SEQUENCE OWNED BY     f   ALTER SEQUENCE public."Routes-Stops_id_route_stopp_seq" OWNED BY public."Routes-Stops".id_route_stop;
          public          postgres    false    226            �            1259    168191    Routes_id_routee_seq    SEQUENCE     �   CREATE SEQUENCE public."Routes_id_routee_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 -   DROP SEQUENCE public."Routes_id_routee_seq";
       public          postgres    false    218            �           0    0    Routes_id_routee_seq    SEQUENCE OWNED BY     P   ALTER SEQUENCE public."Routes_id_routee_seq" OWNED BY public."Routes".id_route;
          public          postgres    false    225            �            1259    160112    Stops    TABLE     n   CREATE TABLE public."Stops" (
    name text,
    location double precision[],
    id_stop integer NOT NULL
);
    DROP TABLE public."Stops";
       public         heap    postgres    false            �            1259    168209    Stops_id_stopp_seq    SEQUENCE     �   CREATE SEQUENCE public."Stops_id_stopp_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 +   DROP SEQUENCE public."Stops_id_stopp_seq";
       public          postgres    false    220            �           0    0    Stops_id_stopp_seq    SEQUENCE OWNED BY     L   ALTER SEQUENCE public."Stops_id_stopp_seq" OWNED BY public."Stops".id_stop;
          public          postgres    false    227            �            1259    160117    Type_Bus    TABLE     U   CREATE TABLE public."Type_Bus" (
    type_name text,
    id_type integer NOT NULL
);
    DROP TABLE public."Type_Bus";
       public         heap    postgres    false            �            1259    168219    Type_Bus_id_typee_seq    SEQUENCE     �   CREATE SEQUENCE public."Type_Bus_id_typee_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 .   DROP SEQUENCE public."Type_Bus_id_typee_seq";
       public          postgres    false    221            �           0    0    Type_Bus_id_typee_seq    SEQUENCE OWNED BY     R   ALTER SEQUENCE public."Type_Bus_id_typee_seq" OWNED BY public."Type_Bus".id_type;
          public          postgres    false    228            8           2604    168154    Buses id_bus    DEFAULT     q   ALTER TABLE ONLY public."Buses" ALTER COLUMN id_bus SET DEFAULT nextval('public."Buses_id_buss_seq"'::regclass);
 =   ALTER TABLE public."Buses" ALTER COLUMN id_bus DROP DEFAULT;
       public          postgres    false    222    215            9           2604    168164    Depots id_depot    DEFAULT     w   ALTER TABLE ONLY public."Depots" ALTER COLUMN id_depot SET DEFAULT nextval('public."Depots_id_depott_seq"'::regclass);
 @   ALTER TABLE public."Depots" ALTER COLUMN id_depot DROP DEFAULT;
       public          postgres    false    223    216            :           2604    168174    Drivers id_driver    DEFAULT     {   ALTER TABLE ONLY public."Drivers" ALTER COLUMN id_driver SET DEFAULT nextval('public."Drivers_id_driverr_seq"'::regclass);
 B   ALTER TABLE public."Drivers" ALTER COLUMN id_driver DROP DEFAULT;
       public          postgres    false    224    217            ;           2604    168192    Routes id_route    DEFAULT     w   ALTER TABLE ONLY public."Routes" ALTER COLUMN id_route SET DEFAULT nextval('public."Routes_id_routee_seq"'::regclass);
 @   ALTER TABLE public."Routes" ALTER COLUMN id_route DROP DEFAULT;
       public          postgres    false    225    218            <           2604    168202    Routes-Stops id_route_stop    DEFAULT     �   ALTER TABLE ONLY public."Routes-Stops" ALTER COLUMN id_route_stop SET DEFAULT nextval('public."Routes-Stops_id_route_stopp_seq"'::regclass);
 K   ALTER TABLE public."Routes-Stops" ALTER COLUMN id_route_stop DROP DEFAULT;
       public          postgres    false    226    219            =           2604    168210    Stops id_stop    DEFAULT     s   ALTER TABLE ONLY public."Stops" ALTER COLUMN id_stop SET DEFAULT nextval('public."Stops_id_stopp_seq"'::regclass);
 >   ALTER TABLE public."Stops" ALTER COLUMN id_stop DROP DEFAULT;
       public          postgres    false    227    220            >           2604    168220    Type_Bus id_type    DEFAULT     y   ALTER TABLE ONLY public."Type_Bus" ALTER COLUMN id_type SET DEFAULT nextval('public."Type_Bus_id_typee_seq"'::regclass);
 A   ALTER TABLE public."Type_Bus" ALTER COLUMN id_type DROP DEFAULT;
       public          postgres    false    228    221            �          0    160089    Buses 
   TABLE DATA           �   COPY public."Buses" (id_driver, id_route, id_depot, on_line, id_type, year_create, registration_number, bus_position, id_bus) FROM stdin;
    public          postgres    false    215   �9       �          0    160094    Depots 
   TABLE DATA           2   COPY public."Depots" (name, id_depot) FROM stdin;
    public          postgres    false    216   N:       �          0    160099    Drivers 
   TABLE DATA           4   COPY public."Drivers" (name, id_driver) FROM stdin;
    public          postgres    false    217   |:       �          0    160104    Routes 
   TABLE DATA           c   COPY public."Routes" (name, overall_time, time_first, time_last, "interval", id_route) FROM stdin;
    public          postgres    false    218   ;       �          0    160109    Routes-Stops 
   TABLE DATA           d   COPY public."Routes-Stops" (id_route, id_stop, "position", time_to_next, id_route_stop) FROM stdin;
    public          postgres    false    219   �;       �          0    160112    Stops 
   TABLE DATA           :   COPY public."Stops" (name, location, id_stop) FROM stdin;
    public          postgres    false    220   <       �          0    160117    Type_Bus 
   TABLE DATA           8   COPY public."Type_Bus" (type_name, id_type) FROM stdin;
    public          postgres    false    221   �<       �           0    0    Buses_id_buss_seq    SEQUENCE SET     A   SELECT pg_catalog.setval('public."Buses_id_buss_seq"', 4, true);
          public          postgres    false    222            �           0    0    Depots_id_depott_seq    SEQUENCE SET     D   SELECT pg_catalog.setval('public."Depots_id_depott_seq"', 2, true);
          public          postgres    false    223            �           0    0    Drivers_id_driverr_seq    SEQUENCE SET     F   SELECT pg_catalog.setval('public."Drivers_id_driverr_seq"', 8, true);
          public          postgres    false    224            �           0    0    Routes-Stops_id_route_stopp_seq    SEQUENCE SET     P   SELECT pg_catalog.setval('public."Routes-Stops_id_route_stopp_seq"', 11, true);
          public          postgres    false    226            �           0    0    Routes_id_routee_seq    SEQUENCE SET     D   SELECT pg_catalog.setval('public."Routes_id_routee_seq"', 3, true);
          public          postgres    false    225            �           0    0    Stops_id_stopp_seq    SEQUENCE SET     B   SELECT pg_catalog.setval('public."Stops_id_stopp_seq"', 6, true);
          public          postgres    false    227            �           0    0    Type_Bus_id_typee_seq    SEQUENCE SET     E   SELECT pg_catalog.setval('public."Type_Bus_id_typee_seq"', 2, true);
          public          postgres    false    228            @           2606    168162    Buses Buses_pkey 
   CONSTRAINT     V   ALTER TABLE ONLY public."Buses"
    ADD CONSTRAINT "Buses_pkey" PRIMARY KEY (id_bus);
 >   ALTER TABLE ONLY public."Buses" DROP CONSTRAINT "Buses_pkey";
       public            postgres    false    215            B           2606    168172    Depots Depots_pkey 
   CONSTRAINT     Z   ALTER TABLE ONLY public."Depots"
    ADD CONSTRAINT "Depots_pkey" PRIMARY KEY (id_depot);
 @   ALTER TABLE ONLY public."Depots" DROP CONSTRAINT "Depots_pkey";
       public            postgres    false    216            D           2606    168182    Drivers Drivers_pkey 
   CONSTRAINT     ]   ALTER TABLE ONLY public."Drivers"
    ADD CONSTRAINT "Drivers_pkey" PRIMARY KEY (id_driver);
 B   ALTER TABLE ONLY public."Drivers" DROP CONSTRAINT "Drivers_pkey";
       public            postgres    false    217            H           2606    168208    Routes-Stops Routes-Stops_pkey 
   CONSTRAINT     k   ALTER TABLE ONLY public."Routes-Stops"
    ADD CONSTRAINT "Routes-Stops_pkey" PRIMARY KEY (id_route_stop);
 L   ALTER TABLE ONLY public."Routes-Stops" DROP CONSTRAINT "Routes-Stops_pkey";
       public            postgres    false    219            F           2606    168200    Routes Routes_pkey 
   CONSTRAINT     Z   ALTER TABLE ONLY public."Routes"
    ADD CONSTRAINT "Routes_pkey" PRIMARY KEY (id_route);
 @   ALTER TABLE ONLY public."Routes" DROP CONSTRAINT "Routes_pkey";
       public            postgres    false    218            J           2606    168218    Stops Stops_pkey 
   CONSTRAINT     W   ALTER TABLE ONLY public."Stops"
    ADD CONSTRAINT "Stops_pkey" PRIMARY KEY (id_stop);
 >   ALTER TABLE ONLY public."Stops" DROP CONSTRAINT "Stops_pkey";
       public            postgres    false    220            L           2606    168229    Type_Bus Type_Bus_pkey 
   CONSTRAINT     ]   ALTER TABLE ONLY public."Type_Bus"
    ADD CONSTRAINT "Type_Bus_pkey" PRIMARY KEY (id_type);
 D   ALTER TABLE ONLY public."Type_Bus" DROP CONSTRAINT "Type_Bus_pkey";
       public            postgres    false    221            �   R   x�5�;
�@D��a$�U�\��6���c+��7o"$yoe�FAI�Q斦���`���)DmD����M���yO2r<���{      �      x�+NM��K�4�J�,*.�4����� P��      �   �   x�����/l���b�/�
츰�Ӑ���@���s/6_l���pqA�`ś/��[/lқ.,k�qa�1Ȅ w+H|��(���6�½�&\%��%��\ep�iƕ���i�1������� a*\X      �   �   x����	1�s�
+Xf�`j��u��d�������?�F�
!�d���	�'\QQ6>3^��T�|������Ԡ��fӠ۬����Ԃ	�|M�8R}����hl7�3�Bq����Ec�6n��$�AD��u~�      �   X   x�U���0��0(n�������P�N>�F�}�X�FК��	t%AG��J��)�)�l�1���?�ƅ�F�rD�����'�O      �   �   x�e�1�0E��,�"iS�]�	�D��b��֨R%j��}#lu�X���6�(Px`�^��KoM}�wtێו�69O�XK_�g_��	Es��KE���	w��d�X�[�f$*-�!����m��
�#�~��W�{�[�0} �s�      �   0   x��0�¦�M�]�x��b#�!ׅ�v_�za�Ŧ�pa#�=... ��     