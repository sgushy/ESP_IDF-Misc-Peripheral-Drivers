set(component_srcs "common/PCA9555.c" "ESP-IDF/PCA9555_Interfaces.c")

idf_component_register(SRCS "${component_srcs}"
                       PRIV_REQUIRES driver
                       INCLUDE_DIRS "." "include/") 
