###
## DIRECCIONES MAC
###

## LEE LAS DIRECCIONES DESDE UNA TABLA XLS 
## ENTREGA UNA TABLA JSON

## LIBRERIAS
library(tidyverse)
library(readODS)
library(jsonlite)

## LECTURA DE ARCHIVOS
path <- "/home/rjnogales/Repos/crm.mio/dataOriginal/"
## ADDRESS MAC
mac <- data.frame(read_ods(path = str_c(path,"macAddress.ods"),
                           col_names = TRUE))

macC <- data.frame()
macCol <- data.frame(str_split(mac$columna1, pattern = "\n"))
colnames(macCol) <- c("arduinoID")
macC <- macCol
macCol <- data.frame(str_split(mac$columna2, pattern = "\n"))
colnames(macCol) <- c("arduinoID")
macC <- bind_rows(macC,macCol)
macCol <- data.frame(str_split(mac$columna3, pattern = "\n"))
colnames(macCol) <- c("arduinoID")
macC <- bind_rows(macC,macCol)
macCol <- data.frame(str_split(mac$columna4, pattern = "\n"))
colnames(macCol) <- c("arduinoID")
macC <- bind_rows(macC,macCol)
macCol <- data.frame(str_split(mac$columna5, pattern = "\n"))
colnames(macCol) <- c("arduinoID")
macC <- bind_rows(macC,macCol)

rm(mac,macCol)

## PLATFORMS
pla <- data.frame(read_ods(path = str_c(path,"estacionesPlataformas220308.ods"),
                           col_names = TRUE))

## ORGANIZAR JSON 
# ARDUINOS
# arduinoID: string
# arduinoStation: String
# arduinoPlatform: string
# arduinoUserLastModifier: string
# arduinoPlatformLastModifier: date

arduinos <- pla %>%
  mutate(arduinoID = "91:c9:08:a1:f6:22") %>%
  mutate(arduinoStation = str_trim(str_sub(ESTACION_PLATAFORMA,1,nchar(ESTACION_PLATAFORMA)-2))) %>%
  mutate(arduinoPlatform = str_sub(ESTACION_PLATAFORMA,nchar(arduinoStation)+1,nchar(ESTACION_PLATAFORMA))) %>%
  mutate(arduinoUserLasModifier = c("ramiro")) %>%
  mutate(arduinoPlaformLastModifier = c(Sys.Date())) %>%
  select(-CORREDOR,-ESTACION_PLATAFORMA)

rm(macC,pla)

## TRANSFORMACION A JSON

aJson <- toJSON(x = arduinos,
                dataframe = 'rows') %>%
  minify()

write_json(aJson,path = str_c(path,"arduinos.json"))


aJson <- toJSON(x = arduinos,
                dataframe = 'rows')
prettify(aJson)
minify(aJson)





