# Fetch the newest code
git init

git add --all

git remote add rduart git@github.com:vspup/duart.git

git fetch rduart master 

git diff rduart/master --name-status

for file in `git diff rduart/master --name-status`
do
    rm -f -- "$file"
done

git diff rduart/master --name-status

git add --all

git pull rduart master