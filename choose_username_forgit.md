
https://superuser.com/questions/232373/how-to-tell-git-which-private-key-to-use

git config core.sshCommand "ssh -i ~/.ssh/id_rsa_example -F /dev/null"
git pull
git push
