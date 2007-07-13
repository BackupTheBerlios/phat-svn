#!/usr/bin/env python

import cairo
from math import pi
import os

W = 32
H = 32

def get_transp_surface( width, height ):
	surf = cairo.ImageSurface( cairo.FORMAT_ARGB32, width, height )

	c = cairo.Context( surf )
	c.set_source_rgba(0, 0, 0, 0)
	c.set_operator (cairo.OPERATOR_SOURCE)
	c.paint()

	return surf


def path_torte( c, ang ):

	c.set_source_rgba( 0.3,0.5,0,0.5 )
	c.arc( W/2, H/2, W*4.5/10, 0, 2*pi )
	c.fill()

	c.set_source_rgba( 0,1,0,0.5 )
	c.move_to( W/2, H/2 )
	c.arc( W/2, H/2, W*3/10, 3*pi/4, 3*pi/4+ang )
	c.fill()

	c.set_source_rgba( 0,1,0.5,0.7 )
	c.arc( W/2, H/2, W*4/10, 3*pi/4, 3*pi/4 )
	c.line_to( W/2, H/2 )
	c.stroke()

	c.set_source_rgba( 0.6,0.3,0.4,0.7 )
	c.arc( W/2, H/2, W*4/10, ang+3*pi/4, ang+3*pi/4 )
	c.line_to( W/2, H/2 )
	c.stroke()

def create_knob_phase( n ):
	s = get_transp_surface( W, H )

	c = cairo.Context( s )
	c.set_operator (cairo.OPERATOR_SOURCE)

	ang = 3*pi/2 * n / 52

	path_torte( c, ang )


	s.write_to_png('output%0d.png' % n )

for i in range(52):
	create_knob_phase( i )


os.system( "( for i in `seq 0 51`; do echo output$i.png; done; echo out.png ) | xargs convert +append" )

