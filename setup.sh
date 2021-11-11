
rm -r src/Rains_of_Rhodianur/resources
mkdir src/Rains_of_Rhodianur/resources

##wget --no-check-certificate 'https://drive.google.com/uc?export=download&id=1RhJkdTCAH59gjmsczXxacW0ZaLV1QXdJ' -O resources.zip

wget --no-check-certificate 'https://www.dropbox.com/sh/by3y5kzb4mbmku4/AADaA6aIEcgTUSPzidPZl2-ja?dl=1' -O resources.zip

mv resources.zip src/Rains_of_Rhodianur/resources/

unzip src/Rains_of_Rhodianur/resources/resources.zip -d src/Rains_of_Rhodianur/resources/

rm src/Rains_of_Rhodianur/resources/resources.zip
