git submodule update --recursive
echo analysis/rooutil
cd analysis/rooutil
git status | head -n 1
git rev-parse HEAD
cd - > /dev/null
echo analysis/plottery
cd analysis/plottery
git status | head -n 1
git rev-parse HEAD
cd - > /dev/null
echo fakerate/plottery
cd fakerate/plottery
git status | head -n 1
git rev-parse HEAD
cd - > /dev/null
echo fakerate/rooutil
cd fakerate/rooutil
git status | head -n 1
git rev-parse HEAD
cd - > /dev/null
echo fakerate/ProjectMetis
cd fakerate/ProjectMetis
git status | head -n 1
git rev-parse HEAD
cd - > /dev/null
echo analysis/ProjectMetis
cd analysis/ProjectMetis
git status | head -n 1
git rev-parse HEAD
cd - > /dev/null
echo wwwbabymaker
cd wwwbabymaker
git status | head -n 1
git rev-parse HEAD
echo sh check_git_hash.sh
sh check_git_hash.sh
cd - > /dev/null
