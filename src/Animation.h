#ifndef ANIMATION_H
#define ANIMATION_H
class Animation
{
public:
	unsigned int index;
	unsigned int frameIndex;
	unsigned int numFrames;
	unsigned int animationSpeed;
	Animation();
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);

private:

};


#endif
