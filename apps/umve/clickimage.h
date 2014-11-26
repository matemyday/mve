#ifndef CLICK_IMAGE_HEADER
#define CLICK_IMAGE_HEADER

#include <QLabel>
#include <QMouseEvent>

/* Scalable image that features click signals. */
class ClickImage : public QLabel
{
    Q_OBJECT

private:
    double scale_factor;
    QPoint get_mouse_coordinates (QMouseEvent* event);

protected:
    void mousePressEvent (QMouseEvent* event);
    void mouseMoveEvent (QMouseEvent* event);
    void mouseReleaseEvent (QMouseEvent* event);

signals:
    void mouse_clicked (int x, int y, QMouseEvent* event);
    void mouse_released (int x, int y, QMouseEvent* event);
    void mouse_moved (int x, int y, QMouseEvent* event);

public:
    ClickImage (void);
    ~ClickImage (void);

    double get_scale_factor (void) const;
    void set_scale_factor (double factor);
    void update_size (void);
};

/* ---------------------------------------------------------------- */

inline
ClickImage::ClickImage (void)
{
    this->scale_factor = 1.0;
}

inline
ClickImage::~ClickImage (void)
{
}

inline double
ClickImage::get_scale_factor (void) const
{
    return this->scale_factor;
}

inline void
ClickImage::set_scale_factor (double factor)
{
    this->scale_factor = factor;
    if (this->scale_factor == 1.0)
        this->adjustSize();
    else
        this->resize(this->scale_factor * this->pixmap()->size());
}

inline void
ClickImage::update_size (void)
{
    this->set_scale_factor(this->scale_factor);
}

inline void
ClickImage::mousePressEvent (QMouseEvent* event)
{
    QPoint const& pnt = this->get_mouse_coordinates(event);
    emit this->mouse_clicked(pnt.x(), pnt.y(), event);
}

inline void
ClickImage::mouseReleaseEvent (QMouseEvent* event)
{
    QPoint const& pnt = this->get_mouse_coordinates(event);
    emit this->mouse_released(pnt.x(), pnt.y(), event);
}

inline void
ClickImage::mouseMoveEvent (QMouseEvent* event)
{
    QPoint const& pnt = this->get_mouse_coordinates(event);
    emit this->mouse_moved(pnt.x(), pnt.y(), event);
}

inline QPoint 
ClickImage::get_mouse_coordinates (QMouseEvent* event)
{
    QPoint pnt(event->pos());

    if (this->hasScaledContents())
    {
        QSize ps(this->pixmap()->size());
        QSize ws(this->size());

        float scale_x = (float)ps.width() / (float)ws.width();
        float scale_y = (float)ps.height() / (float)ws.height();

        pnt.setX((int)((float)pnt.x() * scale_x));
        pnt.setY((int)((float)pnt.y() * scale_y));
    }

    return pnt;
}

#endif /* CLICK_IMAGE_HEADER */
