/*

Engine()
Call create on m_Window to populate the RenderWindow member variable
You can assign a custom resolution or you can call VideoMode::getDesktopMode() to get the screen resolution

run()
Construct a local ClockLinks to an external site. object to track TimeLinks to an external site. per frame
    The time differential (dt) since the last frame will be passed into update
Construct a local Particle to be used for the unit tests.  
The tests will be given to you, and you can use them to check your progress as you go. 
Use the following code exactly:
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
    
After the unit tests are complete, create your game loop
Loop while m_Window is open
    Restart the clock (this will return the time elapsed since the last frame)
    Convert the clock time to seconds
    Call input
    Call update
    Call draw
    
input()
Poll the Windows event queue
  Handle the Escape key pressed and closed events so your program can exit
  Handle the left mouse button pressed event
      Create a loop to construct 5 particles (I used 5, you can change this if you want)
          The numPoints parameter in the Particle constructor is a random number in the range [25:50]
              You can experiment with the range on this number
              It will determine the number of vertices in each particle
          Pass the position of the mouse click into the Particle constructor so it has a starting position
          
update(float dtAsSeconds)
The general idea here is to loop through m_particles and call update on each Particle in the vector whose ttl (time to live) has not expired
    If a particle's ttl has expired, it must be erased from the vector
This is best done with an iterator-based for-loop
    Don't automatically increment the iterator for each iteration
    if getTTL() > 0.0
        Call update on that Particle
            Pass in the time differential since the last frame (dt)
        increment the iterator
    else
        erase the element the iterator points to
        erase returns an iterator that points to the next element after deletion, or end if it is the end of the vector
            Assign the iterator to this return value
        Do not increment the iterator (if you do you might increment past the end of the vector after you delete the last element)
        
draw()
  clear the window
  Loop through each Particle in m_Particles
      Pass each element into m_Window.draw()
      Note:  This will use polymorphism to call your Particle::draw() function
  display the window



*/
