# First install homebrew
ruby -e "$(curl -fsSL https://raw.github.com/mxcl/homebrew/go)"
 
# Choose the name of the virtualenv as simplecv
virtualenv simplecv --no-site-packages
source simplecv/bin/activate
# This activates the virtualenv; your command prompt should change from `$` to `(simplecv)$`
 
# Next the dependencies
sudo easy_install pip  # Can be ignored, if pip already present
brew doctor
brew update
brew upgrade
 
# Its advisable to install numpy and scipy before installing opencv/simplecv
sudo pip install numpy
brew install gfortran  # Fortran compiler - dependency for scipy
sudo pip install scipy
sudo pip install ipython  # SimpleCV also offers an interactive shell which uses ipython notebook; it's pretty great too!
 
# Install OpenCV
brew tap homebrew/science
brew install opencv
# This puts 2 files namely, cv.py and cv2.so in /usr/local/lib/python2.7/site-packages
# In order to use this from the virtualenv, copy these two files and place them in your virtualenv's site-packages
cp /usr/local/lib/python2.7/site-packages/cv* ./simplecv/lib/python2.7/site-packages/
# Test it out:
# (simplecv)$ python
# (simplecv)>>> import cv2
# (simplecv)>>>
 
# Install SDL dependencies
brew install sdl sdl_image sdl_mixer sdl_ttf portmidi
brew tap homebrew/headonly
brew install --HEAD smpeg
# In case if the above doesn't work, then try the following:
# brew install --HEAD https://raw.github.com/Homebrew/homebrew-headonly/master/smpeg.rb
 
# Installing PIL (Python Imaging Library)
curl -O -L http://effbot.org/media/downloads/Imaging-1.1.7.tar.gz
cd Imaging-1.1.7/
python setup.py build --force
sudo python setup.py install
# Check here that at the end it shows that Imaging installed in ./simplecv/lib/python2.7/site-packages/
# Test it out:
# (simplecv)$ python
# (simplecv)>>> import Imaging
# (simplecv)>>>
 
brew install mercurial
sudo pip install hg+http://bitbucket.org/pygame/pygame  # pygame is used for displaying images and videos in SimpleCV
sudo pip install svgwrite
 
# Finally, let's install SimpleCV developer version
git clone https://github.com/sightmachine/SimpleCV.git
cd SimpleCV/
sudo python setup.py install
# Again this should be installed in ./simplecv/lib/python2.7/site-packages/
# Test it out:
# (simplecv)$ simplecv
# This should start a ipython notebook witht the command prompt as `SimpleCV:1>`
