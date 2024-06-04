#ifndef MAPLAYER_H
#define MAPLAYER_H

#pragma once

class Layer
{
	public:
		virtual void Update() = 0;
		virtual void Render() = 0;
};
#endif // LAYER_H