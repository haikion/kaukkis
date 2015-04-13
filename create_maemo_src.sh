./clean.sh
dpkg-buildpackage -rfakeroot -sa -S -I.git -I.pc -I.gitignore -Iclean -I*pro.user
