#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QObject>
#include <QStringList>

#include <QObject>
#include <QStringList>

class ComboBoxModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList items READ items WRITE setItems NOTIFY itemsChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QString currentText READ currentText NOTIFY currentTextChanged)

public:
    explicit ComboBoxModel(QObject *parent = nullptr);

    QStringList items() const;
    void setItems(const QStringList &newItems);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QString currentText() const;

    Q_INVOKABLE void addItem(const QString &item);
    Q_INVOKABLE void clearItems();
    Q_INVOKABLE QString getSelectedItem(); // Метод для получения выбранного элемента

signals:
    void itemsChanged();
    void currentIndexChanged();
    void currentTextChanged();
    void signalConectedPortUpdate();

public slots:
    // Слоты для вызова из QML
//    void handleComboBoxClicked();
//    void onComboBoxClicked();
    void comboBoxOpened();
private:
    QStringList m_items;
    int m_currentIndex = -1;
};


#endif // COMBOBOXMODEL_H
