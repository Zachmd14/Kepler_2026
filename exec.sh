#!/bin/bash

options=("Site web avec toutes les planetes" "Site web avec une seule planetes et ses energies" "Quit")

PS3="Select an option "  # Prompt string

select opt in "${options[@]}"
do
    case $opt in
        "Site web avec toutes les planetes")
            ../bin/release/executable && firefox ../site/site.html
            continue
            ;;
        "Site web avec une seule planetes et ses energies")
            ../bin/release/executable && firefox site_energies/site.html
            continue
            ;;
        "Quit")
            echo "Goodbye!"
            break
            ;;
        *) 
            echo "Invalid option $REPL"
            continue
            ;;
    esac
done

