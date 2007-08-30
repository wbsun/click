// -*- c-basic-offset: 4 -*-
#ifndef CLICK_FULLNOTEQUEUE_HH
#define CLICK_FULLNOTEQUEUE_HH
#include "notifierqueue.hh"
CLICK_DECLS

/*
=c

Queue
Queue(CAPACITY)

=s storage

stores packets in a FIFO queue

=d

Stores incoming packets in a first-in-first-out queue.
Drops incoming packets if the queue already holds CAPACITY packets.
The default for CAPACITY is 1000.

Queue notifies interested parties when it becomes empty and when a
formerly-empty queue receives a packet.  The empty notification takes place
some time after the queue goes empty, to prevent thrashing for queues that
hover around 1 or 2 packets long.  This behavior is the same as that of
NotifierQueue.  Queue additionally notifies interested parties that it is
non-full, and when a formerly-full queue gains some free space.  In all
respects but notification, Queue behaves exactly like SimpleQueue.

You may also use the old element name "FullNoteQueue".

B<Multithreaded Click note:> Queue is designed to be used in an
environment with at most one concurrent pusher and at most one concurrent
puller.  Thus, at most one thread pushes to the Queue at a time and at
most one thread pulls from the Queue at a time.  Different threads can
push to and pull from the Queue concurrently, however.  See MSQueue for
a queue that can support multiple concurrent pushers.

=h length read-only

Returns the current number of packets in the queue.

=h highwater_length read-only

Returns the maximum number of packets that have ever been in the queue at once.

=h capacity read/write

Returns or sets the queue's capacity.

=h drops read-only

Returns the number of packets dropped by the queue so far.

=h reset_counts write-only

When written, resets the C<drops> and C<highwater_length> counters.

=h reset write-only

When written, drops all packets in the queue.

=a SimpleQueue, NotifierQueue, MixedQueue, FrontDropQueue, MSQueue */

class FullNoteQueue : public NotifierQueue { public:

    FullNoteQueue();
    ~FullNoteQueue();

    const char *class_name() const		{ return "Queue"; }
    void *cast(const char *);

    int configure(Vector<String> &conf, ErrorHandler *);
    
    void push(int port, Packet *);
    Packet *pull(int port);

  private:

    ActiveNotifier _full_note;

};

CLICK_ENDDECLS
#endif
