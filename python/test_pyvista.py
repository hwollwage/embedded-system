import pyvista as pv

plotter = pv.Plotter()

plotter.add_mesh(
    pv.Cube(),
    show_edges=True
)

plotter.show()