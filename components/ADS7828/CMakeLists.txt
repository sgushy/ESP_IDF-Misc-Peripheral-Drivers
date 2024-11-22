set(component_srcs "common/ADS7828.c" "ESP-IDF/ADS7828_Interfaces.c")

idf_component_register(SRCS "${component_srcs}"
                       PRIV_REQUIRES driver
                       INCLUDE_DIRS "." "include/") 
