cmake_minimum_required(VERSION 3.29)

project(projekt_rendezvous)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)



# --- Konfiguracja FetchContent dla SFML ---



# 1. Dołącz wbudowany moduł FetchContent

include(FetchContent)



# 2. Zadeklaruj zależność SFML

#    Określa, skąd pobrać bibliotekę (repozytorium Git) i jaką wersję (tag)

FetchContent_Declare(

        SFML

        GIT_REPOSITORY https://github.com/SFML/SFML.git

        GIT_TAG        3.0.2 # Możesz tu wpisać inną stabilną wersję, np. 3.0.0-rc

)



# 3. Pobierz i udostępnij SFML

#    Ten krok faktycznie pobiera kod (jeśli jeszcze nie został pobrany)

#    i sprawia, że cele (targets) SFML są dostępne dla Twojego projektu.

FetchContent_MakeAvailable(SFML)



# --- Twój projekt ---



add_executable(projekt_rendezvous ../Projekt_randezvous/src/main.cpp

        ../Projekt_randezvous/src/Agent.h

        ../Projekt_randezvous/src/Wierzcholek.h

        ../Projekt_randezvous/src/funckje.cpp

        ../Projekt_randezvous/src/funckje_agent.cpp)



# 4. Połącz swój program z bibliotekami SFML

#    SFML dostarcza swoje biblioteki jako cele (targets).

#    Wystarczy je połączyć z Twoim programem.

target_link_libraries(projekt_rendezvous PRIVATE

        sfml-graphics

        sfml-window

        sfml-system

        # Dodaj inne moduły SFML, jeśli ich potrzebujesz, np.:

        # sfml-audio

        # sfml-network

)



# Opcjonalnie: Dla użytkowników Windows, aby ukryć okno konsoli

if(WIN32)

    target_link_options(projekt_rendezvous PRIVATE -mwindows)

endif()